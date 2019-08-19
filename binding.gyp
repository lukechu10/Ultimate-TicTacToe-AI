{
	"targets": [
		{
			"variables": {
				"cpp_base": "./src/cpp/"
			},
			"target_name": "uTicTacToe",
			"sources": [
				"<(cpp_base)node-driver.cpp",
				"<(cpp_base)UltimateTicTacToe.cpp",
				"<(cpp_base)UltimateTicTacToe-minimax.cpp",
				"<(cpp_base)uTicTacToeWrapper.cpp",
				"<(cpp_base)MoveWrapper.cpp",
			],
			"include_dirs": [
				"<!@(node -p \"require('node-addon-api').include\")",
				"./src/include"
			],
			"dependencies": [
				"<!(node -p \"require('node-addon-api').gyp\")"
			],
			"defines": [
				"NAPI_CPP_EXCEPTIONS"
			],
			"msvs_settings": {
				"VCCLCompilerTool": {
					"ExceptionHandling": 1,
					"Optimization": 2
				}
			}
		}
	]
}