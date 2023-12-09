file_path = 'data/test_data_03.txt'
lines = File.readlines(file_path)

row_length = lines[0].size

## Add two line with full dot at the begin and the end
lines.unshift('.' * (row_length - 2))
lines.append('.' * (row_length - 2))

## Part 1
sum = 0

# def append_to_file(filename, string)
#   File.open(filename, "a") do |file|
#     file.puts(string)
#   end
# end

index = 1
# Loop from index 1 to length - 2 (Real content of the input file)
while index < lines.length - 1
  start_index = 0
  end_index = 0
  string_index = 0
  # Loop through all char of the line
  while string_index < row_length
    
    if lines[index][string_index].match(/\d/)
      start_index = string_index
      char_index = start_index
      
      # Loop from start of number
      while char_index < lines[index].length
        if lines[index][char_index].match(/\D/)
          end_index = char_index - 1
          break
        end
        char_index += 1
      end
      # Get the number
      number = lines[index][start_index..end_index].to_i
      # p number # print number to see

      # Add to sum if number close to symbol
      if start_index == 0
        string_1 = lines[index - 1][start_index..(end_index + 1)]
        string_2 = lines[index][start_index..(end_index + 1)]
        string_3 = lines[index + 1][start_index..(end_index + 1)]
        regex = /[^a-zA-Z0-9.\s]/
        sum += number if string_1.match(regex) || string_2.match(regex) || string_3.match(regex)
      end

      if end_index == row_length - 1
        string_1 = lines[index - 1][(start_index - 1)..end_index]
        string_2 = lines[index][(start_index - 1)..end_index]
        string_3 = lines[index + 1][(start_index - 1)..end_index]
        regex = /[^a-zA-Z0-9.\s]/
        sum += number if string_1.match(regex) || string_2.match(regex) || string_3.match(regex)
      end
      if end_index != row_length - 1 && start_index != 0
        string_1 = lines[index - 1][(start_index - 1)..(end_index + 1)]
        string_2 = lines[index][(start_index - 1)..(end_index + 1)]
        string_3 = lines[index + 1][(start_index - 1)..(end_index + 1)]
        regex = /[^a-zA-Z0-9.\s]/
        sum += number if string_1.match(regex) || string_2.match(regex) || string_3.match(regex)
      end
      string_index = end_index 
    end

    # Increase string index
    string_index += 1
  end

  # Increase line index
  index += 1
end

puts sum
