file_path = 'data/test_data_02.txt'
lines = File.readlines(file_path)

## Part 1
sum = 0

lines.each do |line|
  id = line.split(':').first
  content = line.split(':').last

  # Get ID number of Game
  id_number = id.match(/\d+/).to_s.to_i

  # Get all result of Game
  content = content.sub! "\n", ''
  # Split result
  game_results = content.split(';')
  is_posible = true
  
  game_results.each do |game|
    ball_and_type = game.split(',')
    # Init value
    red_number = 0
    green_number = 0
    blue_number = 0    
    # Get number of red, blue and green ball each game
    ball_and_type.each do |bat|
      ball_number = bat.match(/\d+/).to_s.to_i
      ball_type = bat.match(/[a-z]+/).to_s
      

      red_number = ball_number if ball_type == 'red'
      green_number = ball_number if ball_type == 'green'
      blue_number = ball_number if ball_type == 'blue'
    end

    # Check if the game posible
    is_posible = false if red_number > 12 || green_number > 13 || blue_number > 14
  end
  
  sum += id_number.to_i if is_posible
end

p sum

## Part 2
sum = 0

lines.each do |line|
  content = line.split(':').last

  # Get all result of Game
  content = content.sub! "\n", ''
  # Split result
  game_results = content.split(';')

  red_balls, green_balls, blue_balls = Array.new, Array.new, Array.new
  
  game_results.each do |game|
    ball_and_type = game.split(',')
    # Init value
    red_number = 0
    green_number = 0
    blue_number = 0    
    # Get number of red, blue and green ball each game
    ball_and_type.each do |bat|
      ball_number = bat.match(/\d+/).to_s.to_i
      ball_type = bat.match(/[a-z]+/).to_s
      

      red_number = ball_number if ball_type == 'red'
      green_number = ball_number if ball_type == 'green'
      blue_number = ball_number if ball_type == 'blue'
    end
    red_balls.push(red_number)
    green_balls.push(green_number)
    blue_balls.push(blue_number)
  end
  
  sum += red_balls.max * green_balls.max * blue_balls.max
end

p sum
