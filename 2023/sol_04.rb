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
sum = 0 
i = 0
total_of_card = lines.length

result = []
lines.each do |line|
  content = line.gsub(/Card.+\d+:/, '')
  p1 = content.split('|').first
  p2 = content.split('|').last
  a1 = p1.scan(/\d+/)
  a1 = a1.map(&:to_i)
  a2 = p2.scan(/\d+/)
  a2 = a2.map(&:to_i)

  result <<  a2.length - (a2 - a1).length
end

p result
p result.length

@a = Array.new(188, 1)

result[0..5].each_with_index do |x, i_r|
  @a.each_with_index.map do |card, i_c|
    if (i_c).between?(i_r + 1, i_r + x)
      card += card[i_r]
    end
  end
end

p @a
