file_path = '../data/test_data_06.txt'
lines = File.readlines(file_path)

lines.each do |line|
    # Parse input
    one, two, three = line.match(/(turn\son|turn\soff|toggle)\s(\d+,\d+)\sthrough\s(\d+,\d+)/).captures
    puts "--------------------------------------"
    p one 
    p two  
    p three 
end