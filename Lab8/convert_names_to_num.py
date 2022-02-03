with open('training_data.csv', 'r') as file:
    filedata = file.read()

filedata = filedata.replace('glide', '0')
filedata = filedata.replace('flap', '1')

with open('training_data.csv', 'w') as file:
    file.write(filedata)