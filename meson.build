project('magnetar', 'cpp', default_options : ['cpp_std=c++17'])

fusion = dependency('stardustxr-fusion')

files = []

subdir('src')

executable(
	'magnetar',
	files,
	dependencies: [fusion],
)