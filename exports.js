try {
    const uTicTacToe = require("./build/Release/uTicTacToe.node");
    module.exports = uTicTacToe;
}
catch (err) {
    const uTicTacToe = require("./build/Debug/uTicTacToe.node")
    console.warn("You are using a debug build of ultimate-tictactoe-ai. For better performance, use release configuration.");
    module.exports = uTicTacToe;
}