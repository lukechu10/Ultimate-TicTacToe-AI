{
	"targets": [
		{
			"target_name": "uTicTacToe",
			"sources": [
				"./node-driver.cpp",
				"./UltimateTicTacToe.cpp",
				"./UltimateTicTacToe-minimax.cpp",
				"./uTicTacToeWrapper.cpp",
				"./MoveWrapper.cpp"
			],
			"include_dirs": [
				"<!@(node -p \"require('node-addon-api').include\")"
			],
			"dependencies": [ "<!(node -p \"require('node-addon-api').gyp\")" ],
			"defines": [ "NAPI_CPP_EXCEPTIONS" ],
			"msvs_settings": {
				"VCCLCompilerTool": {
					"ExceptionHandling": 1
				}
			},
			"cflags": [
				"-O3"
			]
		}
	]
}