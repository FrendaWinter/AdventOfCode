file_path = 'data/test_data_01.txt'
lines = File.readlines(file_path)

## Part 1
sum = 0
lines.each do |line|
    # Parse input
    one = line.scan(/\d/).first
    two = line.scan(/\d/).last
    sum += (one + two).to_i
end

p sum

## Part 2
sum = 0

str_to_int_hash = {
  # 'zero'  => 0,
  'one'   => "1",
  'two'   => "2",
  'three' => "3",
  'four'  => "4",
  'five'  => "5",
  'six'   => "6",
  'seven' => "7",
  'eight' => "8",
  'nine'  => "9"
}
i = 0
lines.each do |line|
    i += 1
    # Parse input
    one = line.scan(/(\d|one*?|two*?|three*?|four*?|five*?|six*?|seven*?|eight*?|nine*?)/).first
    two = line.scan(/(\d|one*?|two*?|three*?|four*?|five*?|six*?|seven*?|eight*?|nine*?)/).last

    first_number = one[0].to_s
    second_number = two[0].to_s

    first_number = str_to_int_hash[first_number] if first_number.match(/(one|two|three|four|five|six|seven|eight|nine)/)
    second_number = str_to_int_hash[second_number] if second_number.match(/(one|two|three|four|five|six|seven|eight|nine)/)
    # p (first_number + second_number).to_i
    sum += (first_number + second_number).to_i
end

p sum