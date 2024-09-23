file_path = 'data/test_data_04.txt'
lines = File.readlines(file_path)

# Part 1

sum = 0
lines.each do |line|
  content = line.gsub(/Card.+\d+:/, '')
  p1 = content.split('|').first
  p2 = content.split('|').last
  a1 = p1.scan(/\d+/)
  a1 = a1.map(&:to_i)
  a2 = p2.scan(/\d+/)
  a2 = a2.map(&:to_i)
  sum += 2 ** (a2.length - (a2 - a1).length - 1) if (a2.length - (a2 - a1).length) > 0
  
  # p a2
end

p "Part 1: " + sum.to_s
