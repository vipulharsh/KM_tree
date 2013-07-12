This is a tool to compute  coverability trees for Petri Nets. 
- Written by Gregoire Sutre, Jerome Leroux and Vipul Harsh

The tool implements the following algorithms : 

	(km) 	 the original Karp and Miller algorithm .
	(km-red) the Karp and Miller algorithm but with some optimizations.
	(mct) 	 the finkel- mct algorithm
	(mp) 	 the MP algorithm
	(mct2)	 a version of mct in which you can see the difference b/w mp and mct




EXAMPLES:
   Two formats can be used for example files. One the ".net" format or the ".in" format. You can check out the sample examples in the "examples"
   directory.






COMPILATION : 
	use the makefile to compile. Use the CFlAG as per what you wish to do(refer to line no: 7 in GNUmakefile). 
        Do "make"



RUNNING :
   To use the benchmark script, simply use the command " ./benchmark.sh"

   To run the tool on a particular example , use "./objs/kmt <example_name>".
   The executable accepts various options. To view the usage of these options use "./objs/kmt -h"

   To create a dot image, use the -d option while execution. Once it's done, use "dot -Tpdf <dot-file> >> <destination-file.pdf>
