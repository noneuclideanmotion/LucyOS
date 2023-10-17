with open("./generate_key_strings_data/in", "r") as file, open("./generate_key_strings_data/out", "w+") as out:
    
    string = "const char* scancode_to_name_string(uint8_t key_code, keyboard::ps2::scan_set scan_set = keyboard::ps2::scan_set::SCAN_SET_ONE)\n\t{switch(key_code) {\n"
    out.write(string)
    for line in file:
        line = line.strip()
        if line:
            parts = line.split()
            parts[0] = parts[0].upper()
            parts[1] = "0x" + parts[1].upper()
            print(parts[0], parts[1])
            string = "\t\tcase {0}:\n\t\t\treturn \"{1} PRESSED\";\n".format(parts[1],parts[0])
            string+= "\t\tcase {0}:\n\t\t\treturn \"{1} RELEASED\";\n".format(hex(int(parts[1],16)+128),parts[0])
            #string = "template<>\nconst char* scancode_to_name_string<{1}>() {{\n\treturn \"{0} PRESSED\";\n}}\n".format(parts[0],parts[1])
            #string += "template<>\nconst char* scancode_to_name_string<{1}>() {{\n\treturn \"{0} RELEASED\";\n}}\n".format(parts[0],hex(int(parts[1],16)+128))
            print(string)
            out.write(string)
    string = "\t\tdefault:\n\t\t\treturn \"UNKOWN\";\n\t};\n}"
    out.write(string)
        
