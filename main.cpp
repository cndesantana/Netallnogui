#include "BetweennessCentrality.h"

int main(int argc, char **argv)
{
	int t_Output;
	int i_cmatrix;
	string inputfile, outputfile;
	
	if (argc == 4)
	{
		if (argv[2][0]=='d')
		{
			t_Output = 1;
		}
		else
		{
			cerr << endl;
			cerr << "To use: ./BetweennessCentrality network_file type_output output_filename iteration" << endl;
			cerr << endl << "Types of Output: " << endl
			     << "'d' - dendrogram" << endl
			     << "'c' - color matrix" << endl;
			cerr << endl << "iteration: iteration to print color matrix" << endl << endl;
			exit(1);
		}
	}
	else if (argc == 5)
	{
		if ( (argv[2][0]=='c')&&(isdigit(argv[4][0])) )
		{
			t_Output = 2;
			i_cmatrix = atoi(argv[4]);
		}
		else
		{
			cerr << endl;
			cerr << "To use: ./BetweennessCentrality network_file type_output output_filename iteration" << endl;
			cerr << endl << "Types of Output: " << endl
			     << "'d' - dendrogram" << endl
			     << "'c' - color matrix" << endl;
			cerr << endl << "iteration: iteration to print color matrix" << endl << endl;
			exit(1);
		}
	}
	else
	{
		cerr << endl;
		cerr << "To use: ./BetweennessCentrality network_file type_output output_filename iteration" << endl;
		cerr << endl << "Types of Output: " << endl
		     << "'d' - dendrogram" << endl
		     << "'c' - color matrix" << endl;
		cerr << endl << "iteration: iteration to print color matrix" << endl << endl;
		exit(1);
	}
	inputfile.assign(argv[1]);
	outputfile.assign(argv[3]);
	BetweennessCentrality *bca = new BetweennessCentrality(inputfile, outputfile);
	bca->read_Graph();
	if (t_Output == 1)//dendrogram
	{
		bca->calc_Clustering();
	}
	else if (t_Output == 2)//color matrix
	{
		bca->calc_Clustering(i_cmatrix);
	}

	delete(bca);
	return(0);
}
 
