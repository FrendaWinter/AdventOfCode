file_path = '../data/test_data_06.txt'
lines = File.readlines(file_path)

def turn_on(a, b, led_map)
  p 'turn_on'
end

def turn_off(a, b, led_map)
  p 'turn_off'
end

def toggle(a, b, led_map)
  p 'toggle'
end

i = 0
lines.each do |line|
    # Parse input
    one, two, three = line.match(/(turn\son|turn\soff|toggle)\s(\d+,\d+)\sthrough\s(\d+,\d+)/).captures
    puts '--------------------------------------'
    # p one
    first_corner = two.split(',')
    second_corner = three.split(',')
    led_map = Array.new(1000) { Array.new(1000, '0')}

    if one == 'turn on'
      led_map = turn_on(first_corner, second_corner, led_map)
    end
    if one == 'turn off'
      led_map = turn_off(first_corner, second_corner, led_map)
    end
    if one == 'toggle'
      led_map = toggle(first_corner, second_corner, led_map)
    end
    
    i += 1
    break if i > 0
end
