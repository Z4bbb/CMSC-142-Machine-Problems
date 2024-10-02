import re

class TeeClass:
    count = 0  

    def remove_space(self, string):
        leading_whitespace = r'^\s+'
        return re.sub(leading_whitespace, '', string)

    def if_display(self, temp):
        self.count += 1

        if_tokens = []
        rgx = r'[^();]+'

        for match in re.finditer(rgx, temp):
            if_tokens.append(match.group())

        for j in range(2, len(if_tokens)):
            temp = if_tokens[j]
            self.count += 1

    def for_display(self, tokens):
        ctr_instruc = 0
        for_tokens = []
        for_string = ""
        condition_val = 0; 
        initial_val = 0; 

        temp_str = tokens[0]
        for i in range(1, len(tokens)):
            for_string += tokens[i]

        rgx = r'[^()]+'
        for match in re.finditer(rgx, temp_str):
            temp_for = match.group()
            str_for = self.remove_space(temp_for)
            for_tokens.append(str_for)

        temp_for = for_tokens[1]
        component_pattern = r'[^;]+'
        components = list(re.finditer(component_pattern, temp_for))

        for idx, match in enumerate(components):
            init_str = match.group()
            # print(init_str)
            if idx == 0:
                self.count += 1  # Initializer
                initial_pattern = r'(\w+)\s*([<>=!]+)\s*(\w+)'
                initial_comp = list(re.finditer(initial_pattern, init_str))
            
                # Directly access the variable or value after the operator
                for match in initial_comp:
                    value_after_operator = match.group(3)  # Accessing the third group
                    # print(value_after_operator)
                    if(match.group(3).isdigit()):
                        initial_val = int(match.group(3))
                       
            elif idx == 1:
                ctr_instruc += 1  # Condition 
                self.count += 1
                Condition_pattern = r'(\w+)\s*([<>=!]+)\s*(\w+)'
                condition_comp = list(re.finditer(Condition_pattern, init_str))
            
                # Directly access the variable or value after the operator
                for match in condition_comp:
                    value_after_operator = match.group(3)  # Accessing the third group
                    if(match.group(3).isdigit()):
                        condition_val = int(match.group(3))
                        print(condition_val)
                            
            elif idx == 2:
                ctr_instruc += 1  # Update

        sep_str = []
        rgx_colon = r'[^}]+'
        for match in re.finditer(rgx_colon, for_string):
            sep_str.append(self.remove_space(match.group()))

        flag = False
        statement_flag = False

        print(f"test: {ctr_instruc}")

        for j in range(len(sep_str)):
            if 'if' in sep_str[j]:
                temp = sep_str[j]
                if_tokens = []
                rgx = r'[^();]+'

                for match in re.finditer(rgx, temp):
                    if_tokens.append(match.group())

                for j in range(2, len(if_tokens)):
                    temp = if_tokens[j]
                    # print(self.remove_space(temp))
                    if j != len(if_tokens) - 1:
                        print()

                flag = True

            elif 'else' in sep_str[j]:
                temp = sep_str[j]
                else_str = []
                rgx = r'[^{}]+'

                for match in re.finditer(rgx, temp):
                    else_str.append(match.group())

                # for i in range(1, len(else_str)):
                #     print(self.remove_space(else_str[i]))

                flag = True

            elif not statement_flag:
                temp_str = sep_str[j]
                forStr = ''
                
                rgx = r'[^;]+'

                for match in re.finditer(rgx, temp_str):
                    forStr+=match.group()
                    print(forStr)

                rgx_last = r'[^=+-]+'

                for match in re.finditer(rgx_last, forStr):
                    print(f"check: {match.group()}")
                    if match.group():  # This will be True if match.group() is not empty
                        ctr_instruc += 1
             
                statement_flag = True

            else:
                temp_str = sep_str[j]
                statement_str = []
                rgx = r'[^,=]+'

                # for match in re.finditer(rgx, temp_str):
                    # print(self.remove_space(match.group()))
        
        # print(f"check {condition_val}")

        if condition_val==0:
            print(f"T(n) = {ctr_instruc}n", end="")
            if self.count:
                print(f" + {self.count}")
            else:
                print()
        elif(condition_val):
            print(ctr_instruc)
            print(condition_val)
            print(initial_val)
            print(self.count)
            sum = (ctr_instruc * (condition_val - initial_val + 1)) + self.count
            print(f"T(n) = {sum}")


    def display(self, tokens):
        size = len(tokens)
        flag = False
        for_flag = False

        for i in range(size):
            str_token = tokens[i]
            temp = re.sub(r'^\s+', '', str_token)

            if 'for' in temp:
                self.for_display(tokens)
                for_flag = True
                break
            elif 'if' in temp:
                self.if_display(temp)
                flag = False
            elif 'else' in temp:
                else_str = []
                rgx = r'[^{}]+'

                for match in re.finditer(rgx, temp):
                    else_str.append(match.group())

                # for i in range(1, len(else_str)):
                #     print(self.remove_space(else_str[i]))

                flag = True
            else:
                if not flag:
                    flag = True
                self.count += 1

        if not for_flag:
            print(f"T(n) = {self.count}")

    def tokenize(self, snippet):
        tokens = []

        remove_pattern = r'\b(?:int|char)\b'
        result = re.sub(remove_pattern, '', snippet)

        space_pattern = r'\s+'
        result = re.sub(space_pattern, ' ', result)

        trim_pattern = r'^\s+|\s+$'
        result = re.sub(trim_pattern, '', result)

        if 'for' in snippet:
            rgx = r'[^{}]+'
            for match in re.finditer(rgx, result):
                tokens.append(match.group())
        else:
            rgx = r'[^,;]+'
            temp_str = ''
            for match in re.finditer(rgx, result):
                if any(op in match.group() for op in ['=', '<<', '>>', '<', '>']):
                    if ',' not in match.group():
                        temp_str += ','
                    temp_str += match.group()

            rgx_last = r'[^+-;]+'
            for match in re.finditer(rgx_last, temp_str):
                tokens.append(match.group())

        self.display(tokens)

def main():
    tc = TeeClass()

    line = int(input())
    snippet = ''
    ctr = 0

    while ctr < line:
        input_line = input()
        snippet += input_line
        ctr += 1

    tc.tokenize(snippet)

if __name__ == "__main__":
    main()
