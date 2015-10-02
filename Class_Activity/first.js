var firstApp = angular.module('firstApp', []);
firstApp.controller('FirstController', function($scope,$filter) {
  $scope.first = 'Some';
  $scope.last = 'One';
  $scope.heading = 'Message: ';
  $scope.updateMessage = function() {
    $scope.message = 'Hello ' + $filter("uppercase")($scope.first) +' '+ $filter("uppercase")($scope.last) + '!';
  };
  $scope.lowerMessage = function() {
    $scope.message = 'Hello ' + $filter("lowercase")($scope.first) +' '+ $filter("lowercase")($scope.last) + '!';
  };
});