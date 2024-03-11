file_path = '../data/test_data_05.txt'
lines = File.readlines(file_path)

# Part 1
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

# Part 2

result = 0
def check_pair(input_string)
    for i in 1..input_string.length - 2 do
        pair = input_string[i - 1] + input_string[i]
        if input_string[(i + 1)..input_string.length - 1].include? pair
            return true
        end
    end
    return false
end

def check_repeat(input_string)
    for i in 2..input_string.length - 1 do
        if input_string[i] == input_string[i - 2]
            return true
        end
    end
    return false
end

result = 0
lines.each do |line|
    if check_repeat(line) && check_pair(line)
        result += 1
    end
end

puts result