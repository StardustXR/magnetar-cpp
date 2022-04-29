resources = [
	'cell.glb',
	'divider.glb',
]

custom_target(
	'cp_resources',
	input : resources,
	output : resources,
	command : ['cp', '@INPUT@', '@OUTDIR@'],
	install : false,
	build_by_default : true
)