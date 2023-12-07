file_path = 'data/test_data_02.txt'
lines = File.readlines(file_path)

## Part 1
sum = 0
i = 0
lines.each do |line|
  # Parse input
  break if i > 0
  id = line.split(':').first
  content = line.split(':').last

  id_number = id.match(/\d+/).to_s.to_i
  p id_number
  content = content.sub! "\n", ''
  game_results = content.split(';')
  p game_results

  game_results.each do |game|
    ball_and_type = game.split(',')

    ball_and_type.each do |bat|
      
      ball_number = bat.match(/\d+/).to_s.to_i
      ball_type = bat.match(/[a-z]+/).to_s

      p ball_number
      p ball_type
      
      red_number = ball_number if ball_type == 'red'
      green_number = ball_number if ball_type == 'green'
      blue_number = ball_number if ball_type == 'blue'

      p red_number if red_number > 1 && !red_number.nil?
    end
  end

  i += 1
  # two = line.scan(/\d/).last
  # sum += (id).to_i
end

p sum
