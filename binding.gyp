{
	'targets': [{
		'target_name': 'vinput',
		'include_dirs': [
			"<!(node -e \"require('nan')\")"
		],
		'sources': [
			'src/vinput.h',
			'src/interface.cc',
		],
		"conditions":[
			["OS=='win'",
				{
					"sources": [ 
						"src/win32/main.cc",
					],
				},
			]
		],
	}]
}