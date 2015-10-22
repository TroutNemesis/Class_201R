/**
 * This array of pokemon will represent a piece of data in our 'database'
 */
var pokemon = [
  {
    name: 'Pikachu',
    avatarUrl: 'http://i1132.photobucket.com/albums/m580/KimKutThroat/pickachu.gif'
  },
  {
    name: 'Charmander',
    avatarUrl: 'http://24.media.tumblr.com/tumblr_ma0tijLFPg1rfjowdo1_500.gif'

  },
  {
    name: 'Mew',
    avatarUrl: 'http://media3.giphy.com/media/J5JrPT8r1xGda/giphy.gif'
  },
  {
    name: 'Cubone',
    avatarUrl: 'http://rs1169.pbsrc.com/albums/r511/nthndo/tumblr_ljsx6dPMNm1qii50go1_400.gif~c200'
  },
  {
    name: 'Cleffa',
    avatarUrl: 'http://media1.giphy.com/media/pTh2K2xTJ1nag/giphy.gif'
  },
  {
    name: 'Gengar',
    avatarUrl: 'https://s-media-cache-ak0.pinimg.com/originals/7e/3b/67/7e3b67c53469cc4302035be70a7f2d60.gif'
  }
];

var places = [
  {
    name: 'Provo, UT',
    lat: '40.233844',
    lng: '-111.658534',
    avatarUrl: 'http://www.airphotona.com/stockimg/images/07351.jpg'
  },
  {
    name: 'Denver, CO',
    lat: '39.739236',
    lng: '-104.990251',
    avatarUrl: 'http://www.stapletondenver.com/wp-content/uploads/2014/12/denver-skyline.jpg'

  },
  {
    name: 'Pine Grove, CA',
    lat: '38.413352',
    lng: '-120.659131',
    avatarUrl: 'http://s3-media2.fl.yelpcdn.com/bphoto/uaQxBxalzFRiCv7jueL7eA/ls.jpg'
  },
  {
    name: 'Woodland Park, CO',
    lat: '38.993881',
    lng: '-105.056930',
    avatarUrl: 'https://upload.wikimedia.org/wikipedia/commons/thumb/1/1a/WPDowntown.jpeg/250px-WPDowntown.jpeg'
  },
  {
    name: 'Milford, NH',
    lat: '42.835362',
    lng: '71.648984',
    avatarUrl: 'https://milfordnhgop.wildapricot.org/Resources/Pictures/Milford_Pic%201.jpg'
  },
  {
    name: 'Belmont, MA',
    lat: '42.395640',
    lng: '71.177611',
    avatarUrl: 'https://upload.wikimedia.org/wikipedia/commons/b/b1/Town_Hall,_Belmont,_MA.JPG'
  }
];

var people = [
    {
        name: 'Nathan Fillion',
        age: '44',
        avatarUrl: 'https://upload.wikimedia.org/wikipedia/commons/thumb/4/49/Nathan_Fillion_-_Guardians_of_the_Galaxy_premiere_-_July_2014_%28cropped%29.jpg/220px-Nathan_Fillion_-_Guardians_of_the_Galaxy_premiere_-_July_2014_%28cropped%29.jpg'        
    },
    {
        name: 'Rosemary Mix Wixom',
        age: '66',
        avatarUrl: 'http://img.deseretnews.com/images/article/midres/1515012/1515012.jpg'    
    },
    {
        name: 'Morgan Freeman',
        age: '78',
        avatarUrl: 'https://upload.wikimedia.org/wikipedia/commons/thumb/5/57/Morgan_Freeman_-_Discovery_Shoot_%286559314831%29.jpg/220px-Morgan_Freeman_-_Discovery_Shoot_%286559314831%29.jpg'    
    },
    {
        name: 'Norah Jones',
        age: '36',
        avatarUrl: 'https://upload.wikimedia.org/wikipedia/commons/thumb/9/97/Norah.jpg/220px-Norah.jpg'    
    },
    {
        name: 'Leonardo DiCaprio',
        age: '40',
        avatarUrl: 'http://media2.popsugar-assets.com/files/2014/02/04/869/n/1922398/3bb517bc63c6714c_464141555.jpg.xxxlarge/i/Leonardo-DiCaprio-40.jpg'    
    },
    {
        name: 'Judi Dench',
        age: '80',
        avatarUrl: 'https://upload.wikimedia.org/wikipedia/commons/thumb/a/ae/Judi_Dench_at_the_BAFTAs_2007.jpg/220px-Judi_Dench_at_the_BAFTAs_2007.jpg'    
    }
    ]

var http = require('http');
var url = require('url');
var fs = require('fs');
var ROOT_DIR = "src/";
var port = 3000;

http.createServer(function (req, res) {
  var urlObj = url.parse(req.url, true, false);

  if (urlObj.pathname === '/pokemon') {
        res.writeHead(200);
      res.end(JSON.stringify(pokemon));
  } 
  else if(urlObj.pathname === '/places'){
        res.writeHead(200);
      res.end(JSON.stringify(places));
      
  }
  else if(urlObj.pathname === '/people'){
        res.writeHead(200);
      res.end(JSON.stringify(people));
  }else {
    fs.readFile(ROOT_DIR + urlObj.pathname, function (err, data) {
      if (err) {
        res.writeHead(404);
        res.end(JSON.stringify(err));
        return;
      }
      res.writeHead(200);
      res.end(data);
    });
  }

}).listen(port);

console.log('app is now running on port: ' + port)

