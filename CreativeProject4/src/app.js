var app = window.angular.module('app', [])

app.factory('dataFetcher', dataFetcher)
app.controller('mainCtrl', mainCtrl)

function dataFetcher ($http) {

  
  return {
    get: function (dataType) {
    var API_ROOT = dataType
    //window.alert(dataType);
      return $http
        .get(API_ROOT)
        .then(function (resp) {
          return resp.data
        })
    }
  }

}

function mainCtrl ($scope, dataFetcher) {
  $scope.info = []
//   dataFetcher.get()
//     .then(function (data) {
//       $scope.info = data
//     })
    $scope.todoAdd = function() {
       //window.alert($scope.dataType);
        dataFetcher.get($scope.dataType)
        .then(function (data) {
        $scope.info = data
        
        var poke;
        var map = document.getElementById('map');
        var place;
        var people;
        if($scope.dataType === 'pokemon') {
            //window.alert('if');
            poke = document.getElementById('pokemonIf');
            place = document.getElementById('places');
            people = document.getElementById('people');
            people.style.display = 'none'
            poke.style.display = 'block';
            place.style.display = 'none'
            map.style.display = 'none';
        }
        else if ($scope.dataType === 'places') {
            //window.alert('else');
            place = document.getElementById('places');
            poke = document.getElementById('pokemonIf');
            people = document.getElementById('people');
            people.style.display = 'none'
            place.style.display = 'block';
            poke.style.display = 'none'
            map.style.display = 'block';
            google.maps.event.trigger(map, 'resize');
            var currCenter = {lat: 38.8833, lng: -77.0167};
            map.setCenter(currCenter);
            
        }
        else if ($scope.dataType === 'people') {
            //window.alert('else');
            place = document.getElementById('places');
            poke = document.getElementById('pokemonIf');
            people = document.getElementById('people');
            people.style.display = 'block'
            place.style.display = 'none';
            poke.style.display = 'none'
            map.style.display = 'none';
        }
        
    })};
    
  
}
