image_load()

local output = {}

w = image_get_width()
h = image_get_height()

table.insert(output, "image width: " .. w)
table.insert(output, "image height: " .. h)

image_resize(100, 200)
image_crop(40, 30)

image_write("foo/bar.jpg")

return table.concat(output, ", ")
