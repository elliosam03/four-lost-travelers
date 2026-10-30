import re, getopt, sys
class Ratio:
    def __init__(self):
        self.total_lines = 0
        self.code_lines = 0
        self.comment_lines = 0
    def calculate_cpp_comment_ratio(self,filepath):
        """
        Calculates the code-to-comment ratio for a given C++ file.

        Args:
            filepath (str): The path to the C++ source file.

        Returns:
            float: The comment-to-code ratio, or None if the file cannot be read
                or if there are no code lines.
        """
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                lines = f.readlines()
        except FileNotFoundError:
            print(f"Error: File not found at {filepath}")
            return None
        except Exception as e:
            print(f"Error reading file: {e}")
            return None
        heading_parts = [r"/\* Program name: .*",r"\*? Author: .*",r"\*? Date last updated: .*", r"\*? Purpose: .*",]
        total_lines = 0
        code_lines = 0
        comment_lines = 0
        in_multiline_comment = False

        for line in lines:
            line = line.strip()
            if not line:  # Ignore blank lines
                continue

            total_lines += 1

            if in_multiline_comment:
                if '*/' in line:
                    in_multiline_comment = False
                    # If '*/' is on the same line as code, consider it a code line
                    if line.strip().split('*/')[1]:
                        code_lines += 1
                    continue
                heading = False
                for part in heading_parts[1:]:
                    if re.search(part, line, re.IGNORECASE) != None:
                        heading = True
                        break
                if not heading:
                    comment_lines += 1
                continue

            if line.startswith('//'):
                comment_lines += 1
            elif line.startswith('/*'):
                if re.search(heading_parts[0],line,re.IGNORECASE) == None:
                    comment_lines += 1
                if '*/' not in line:  # Multi-line comment starts
                    in_multiline_comment = True
                else:  # Multi-line comment starts and ends on the same line
                    pass
            else:
                # Check for inline comments
                if '//' in line:
                    # If code exists before the inline comment
                    if line.split('//')[0].strip():
                        code_lines += 1
                        comment_lines += 1
                    else: # Only comment after potential whitespace
                        comment_lines += 1
                elif '/*' in line and '*/' in line:
                    # If code exists before and/or after the block comment
                    if line.split('/*')[0].strip() or line.split('*/')[-1].strip():
                        code_lines += 1
                        comment_lines += 1
                    else:
                        comment_lines += 1
                elif '/*' in line:
                    # Code before a multi-line comment start
                    if line.split('/*')[0].strip():
                        code_lines += 1
                    comment_lines += 1
                    in_multiline_comment = True
                else:
                    code_lines += 1

        if code_lines == 0:
            return 0.0  # Avoid division by zero if no code lines are found
        # print(comment_lines)
        # print(code_lines)
        self.code_lines += code_lines
        self.comment_lines += comment_lines
        self.total_lines += total_lines
        return comment_lines / code_lines
    def calculate_final_comment_ratio(self):
        return self.comment_lines / self.code_lines


args = sys.argv[1:]
options = "hf:"
long_options = ["Help", "File="]
cr = Ratio()
try:
    arguments, values = getopt.getopt(args, options, long_options)
    for currentArg, currentVal in arguments:
        if currentArg in ("-h", "--Help"):
            print("Showing Help")
        elif currentArg in ("-f", "--File"):
            #print("Output mode:", currentVal)
            ratio = cr.calculate_cpp_comment_ratio(currentVal)
            if ratio is not None:
                print(f"Comment-to-code ratio for {currentVal}: {ratio*100:.2f}%")
    for filename in values:
        ratio = cr.calculate_cpp_comment_ratio(filename)
        if ratio is not None:
            print(f"Comment-to-code ratio for {filename}: {ratio*100:.2f}%")
    ratio = cr.calculate_final_comment_ratio()
    if ratio is not None:
         print(f"Total Comment-to-code ratio: {ratio*100:.2f}%")
    if ratio > .1:
        print("pass")
    else:
        print("fail")
        sys.exit(1)
except getopt.error as err:
    print(str(err))


