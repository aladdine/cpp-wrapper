#include <stdio.h>
#include <stdlib.h>
#include "sscapi.h"

int main(int argc, char *argv[]) {
	
//	printf("Number of arguments %i files \n",  argc);

    int i;

	for (i = 0; i < argc; i = i + 1 ){
//		printf("List of arguments: %s \n",  argv[i]);
	}	

	if ( argc < 2 )
	{
		printf("usage: pvwatts.exe <weather-file>\n");
		return -1;
	}
 
	// run PVWatts simulation for the specified weather file
	ssc_data_t data = ssc_data_create();
	
	if ( data == NULL )
	{
		printf("error: out of memory.\n");
		return -1;
	}


	double capital_cost;
	
	capital_cost = strtod(argv[1],NULL); 

	double annual_fixed_operating_cost;

	annual_fixed_operating_cost = strtod(argv[2],NULL); 

	double annual_variable_operating_cost;

	annual_variable_operating_cost = strtod(argv[3],NULL);

	double fixed_operating_cost;

	fixed_operating_cost = strtod(argv[4],NULL);

	double variable_operating_cost;

	variable_operating_cost = strtod(argv[5],NULL); 

	double fixed_charge_rate;

	fixed_charge_rate = strtod(argv[6],NULL);

	double annual_energy;

	annual_energy = strtod(argv[7], NULL);

	ssc_data_set_number( data, "capital_cost", capital_cost );
	ssc_data_set_number( data, "annual_fixed_operating_cost", annual_fixed_operating_cost);
	ssc_data_set_number( data, "annual_variable_operating_cost", annual_variable_operating_cost);
	ssc_data_set_number( data, "fixed_operating_cost", fixed_operating_cost ); 
	ssc_data_set_number( data, "variable_operating_cost", variable_operating_cost );
	ssc_data_set_number( data, "fixed_charge_rate", fixed_charge_rate );     
	ssc_data_set_number( data, "annual_energy", annual_energy ); 
	
	ssc_module_t module = ssc_module_create( "lcoefcr" );
	
	if ( NULL == module )
	{
		printf("error: could not create 'pvwattsv5' module.\n");
		ssc_data_free( data );
		return -1;
	}

	if ( ssc_module_exec( module, data ) == 0 )
	{
		printf("error during simulation.\n");
		ssc_module_free( module );
		ssc_data_free( data );
		return -1;
	}
	
//	double lcoe_fcr;

	ssc_number_t lcoe_fcr;

	ssc_data_get_number( data, "lcoe_fcr", &lcoe_fcr );

	printf("%f", lcoe_fcr);
	
	
//	printf("lcoe_fcr %f \n", lcoe_fcr);
	
	
	ssc_module_free( module );
	ssc_data_free( data );
	
	return 0;
}