{
  "targets": [
    {
      "target_name": "binding",
      "sources": [
        "./node-driver.cpp",
        "./UltimateTicTacToe.cpp",
        "./uTicTacToeWrapper.cpp",
		"./MoveWrapper.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "dependencies": [ "<!(node -p \"require('node-addon-api').gyp\")" ],
	  "defines": [ "NAPI_CPP_EXCEPTIONS" ]
    }
  ]
}