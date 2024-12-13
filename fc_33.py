with open('FC_3.txt', 'r') as input_file:
    with open('column1.txt', 'w') as column1_file, open('column2.txt', 'w') as column2_file:
        for line in input_file:
            col1, col2 = line.strip().split(',')
            column1_file.write(col1 + '\n')
            column2_file.write(col2 + '\n')