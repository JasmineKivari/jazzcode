'use strict';
const mongoose = require('mongoose');

const portagesModel = mongoose.model('portage');

const portageTimesReadOne = function (req, res) {
    portagesModel
      .findById(req.params.portageid)
      .exec ( function(err, portages) {
        res
        .status(200)
        .json(portages);


});
};

module.exports = {
    portageTimesReadOne
};