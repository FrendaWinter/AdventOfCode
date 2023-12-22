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

p sum

# Part 2

# sum = 0
# i = 0

# total_of_card = lines.length

# lines.each do |line|
#   i += 1
#   sum +=1
#   content = line.gsub(/Card.+\d+:/, '')
#   p1 = content.split('|').first
#   p2 = content.split('|').last
#   a1 = p1.scan(/\d+/)
#   a1 = a1.map(&:to_i)
#   a2 = p2.scan(/\d+/)
#   a2 = a2.map(&:to_i)

#   p  a2.length - (a2 - a1).length

#   sum += a2.length - (a2 - a1).length
#   # if i + 10 < total_of_card
#   #   sum += a2.length - (a2 - a1).length
#   # else
#   #   if i + (a2.length - (a2 - a1).length) >= total_of_card
#   #     sum += total_of_card - i
#   #   else
#   #     sum += (a2.length - (a2 - a1).length)
#   #   end
#   # end
# end

# p sum
