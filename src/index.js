var cpp_wrapper = require('./cpp-wrapper.js');

module.exports = {
	run: function(path, inputs){
		return cpp_wrapper.runProgram(path, inputs, function(data){
			console.log("data", data);
			return data
		});
	}
}