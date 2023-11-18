file_path = '../data/test_data_05.txt'
lines = File.readlines(file_path)

result = 0
lines.each do |line|
    if line.scan(/[aeiou]/).count >= 3 && line.match(/\b\w*?(\w{2})\w*?\1\w*?\b/) && !line.match(/(ab|cd|pq|xy)/)
        result += 1
    end
end

puts result