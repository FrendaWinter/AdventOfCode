require 'digest/md5'

input = 'ckczppom'
# Part 1
i = 0
while true
    md5_hash = Digest::MD5.hexdigest(input + i.to_s)
    if md5_hash[0, 5] == '00000'
        puts i
        break
    else
        i += 1
    end
end
# Part 2
i = 0
while true
    md5_hash = Digest::MD5.hexdigest(input + i.to_s)
    if md5_hash[0, 6] == '000000'
        puts i
        break
    else
        i += 1
    end
end