const express = require("express");
const server = express();

server.use("/public", express.static(__dirname + "/build"));

server.get("/*", (req, res) => {
  res.sendFile(__dirname + "/build/index.html");
});

const port = process.env.PORT || 8000;
server.listen(port, () => console.log("Server running on port " + port));
