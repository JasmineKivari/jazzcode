'use strict';
const mongoose = require('mongoose');

const portagesModel = mongoose.model('portage');



const portagesListByOrigin = function (req, res) {
    portagesModel
      .find()
      .exec ( function(err, portages) {
    res
      .status(200)
      .json(portages);


});
};



module.exports = {
    portagesListByOrigin,
   
};