const http = require("http");
const fs = require("fs");
const path = require("path");

const port = 3030;
const projectName = "calculate_primes";

/**
 * dependency 없는 간단한 static web server
 */
const server = http.createServer((req, res) => {
    if (path.normalize(decodeURI(req.url)) !== decodeURI(req.url)) {
        res.statusCode = 403;
        res.end();
        return;
    }

  const relativePath = req.url.substr(1);
  const filePath = path.resolve(__dirname, relativePath);
  const ext = req.url.substr(req.url.lastIndexOf(".") + 1);
  const contentType =
    ext === "html"
      ? "text/html"
      : ext === "js"
      ? "application/javascript"
      : ext === "wasm"
      ? "application/wasm"
      : "text/plain";

  console.log(`request >> ${relativePath}`);
  fs.readFile(filePath, (err, data) => {
    if (!err) {
      res.writeHead(200, {
        "Content-type": contentType,
      });
      res.write(data);
      res.end();
    } else {
      res.writeHead(500);
      res.write('Server Error')
      res.end();
    }
  });
});

server.listen(port, () => {
  console.log(`server start on localhost:${port}`);
});
