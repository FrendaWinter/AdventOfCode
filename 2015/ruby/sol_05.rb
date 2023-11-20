file_path = '../data/test_data_05.txt'
lines = File.readlines(file_path)

def check_duplicates(input_string)
    for i in 1..input_string.length do
        if input_string[i] == input_string[i - 1]
            return true
        end
    end
    return false
end

result = 0
lines.each do |line|
    if line.scan(/[aeiou]/).count >= 3 && check_duplicates(line) && !line.match(/(ab|cd|pq|xy)/)
        result += 1
    end
end

puts result