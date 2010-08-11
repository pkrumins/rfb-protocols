This is a C++ node.js module that decodes various RFB encoding protocols to
RGB buffers (or BGR buffers).

It was written by Peteris Krumins (peter@catonmat.net).
His blog is at http://www.catonmat.net  --  good coders code, great reuse.

------------------------------------------------------------------------------

This module is useful for producing images from various RFB encodings. For
example, if you use it together with node-png (github.com/pkrumins/node-png),
then you can easily produce PNG images by combining the output of this module
with input of node-png.

For now it has only hextile encoding. Next up diffed hextile.

Hextile Encoding
----------------

Example usage:

    var Hextile = require('rfb-protocols').Hextile;
    var Png = require('png').Png;

    var decoder = new Hextile(); // ?? width height?
    decoder.push(buffer, x, y); // ??

    decoder.decode('rgb', function (rgb_buffer, error) {
        new Png(rgb, width, height).encode(function (image, error) {
            fs.writeFileSync(image, 'frame.png', 'binary');
        });
    });

------------------------------------------------------------------------------


Have fun decoding those RFB protocols!


Sincerely,
Peteris Krumins
http://www.catonmat.net

