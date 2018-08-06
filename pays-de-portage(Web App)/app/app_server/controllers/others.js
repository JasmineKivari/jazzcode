'use strict';
const request = require('request');

const apiOptions = {
    server: 'http://192.168.99.100:3000/api/'
};

if (process.env.NODE_ENV === 'production') {
    apiOptions.server =
    'http://pays-de-portage.deploy.cs.camosun.bc.ca/api/';
}

const about = function(req, res) {
	
	res.render('about', { title: 'About Pays De Portage',
                            aboutUs: 'Pays De Portage is a historical tour based on the traditional mode of transportation based on the Ojibwe people of lake superior. Portages are trails that connect two navigable waterways along lake superior to other locations. Depending on your skill level you can choose to portage from our longest trip which is from Thunder Bay Ontario to Pays Plat First Nation, or to the shortest trip which is from Rossport Ontario to Pays Plat First Nation. All of our tours will go around lake superior and will tour the ancient historical pictograph left behind by the Ojibwe people. The tour will end at Pays Plat first nation where cultural exchange and exploration will take place.'
                        });
};

module.exports = {
	about
};
