project('magnetar', 'cpp', default_options : ['cpp_std=c++17'])

fusion = dependency('stardustxr-fusion', version: '>=0.9.0')
glm = dependency('glm')

files = []

subdir('res')
subdir('src')

executable(
	'magnetar',
	files,
	dependencies: [fusion, glm],
)