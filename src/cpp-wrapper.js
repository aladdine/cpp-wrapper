var spawn = require('child_process').spawn;

module.exports = {

	runProgram: function(path,inputs, callback){ // './lcoefcr.exe'

		child = spawn(path,inputs);

		output = "";

		child.stdout.on('data', (data) => {
		//	console.log('stdout data : ' + data);
			output += data;
		});

		child.stderr.on('data', (data) => {
	  	//	console.log('stderr data : ' + data);
		});

		child.on('exit', (code) => {
		//	console.log('stdout data end' + output + "/");
			callback(code);
		});	

	}
}