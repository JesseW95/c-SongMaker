#coms327p3
**Design Decisions:**
	
	**New Data Structures**
	Following the advice from piazza I decided to create data structures to keep track of each wave, sound, and song note
	
	
	**Creating the structs**
	I iterate through the file numerous times to correctly get the amount of memory needed to be allocated for each
	struct. I then parse this data using strtok to put it into each struct member.
	
	**writeSong function**
	Here I create a song struct, the samples are set to 0 and its size is equal to the longest note * sampleRate

# coms327p1

**Design decisions:**

    **genDTMF function**
    When combining two sine waves (sin(x) + sin(x2))/2 I decided using the gensine function would become cumbersome
    having to call it twice per char input. Thus I decided to create a function called genDTMF that took two frequencies
    and replicated the function of gensine twice, while combining the two and averaging them.
    
    **charInput**
    I decided to use a switch case for this, so that I could accept all inputs without issues
    the ones not specified could just output silence. I then set up a 2d array of all the frequencies in a 2x4 array
    in each case I called the genDTMF with the 2 frequencies from the array.
    
    **Writing to file**
    In my main function I use `fopen("output", "w");` this is so that existing outputs will be overwritten.
    In my gensnd functions I use `fopen("output", "a");` so that the text is appended.
    
    **main2**
    Here I ask for a string input of 10 characters.
    My for loop goes from 0-9, calling charInput each iteration and getting the
    char from the in array.
    On the 9th iteration we stop outputting silence so that there isn't a pause at the end.
    
    **main**
    We get the 3 floats required for gensine, then iterate for the sample rate * time, sample rate is how often we sample a second after all.
    we then call gensine each iteration, changing i to the current index.
	
#coms327p2
**Design Decisions:**
	
	**genDTMF2 function**
	With pointer and the new gensine function I was able to use 2 pointers and iterate through all of their samples and combine them
	then divide by 2 to average them. I stored these values in a new pointer before freeing up the other memory.
	
	**genSilence**
	I took my old genSilence function and changed it to create a pointer and fill its samples with 0s. I encountered a bug with this 
	function because I failed to initialize all struct data members which resulted in a sigsev error.
	
	**genSine2**
	I used the same logic from genSine one, but incorporated my loop from the main function of part a.
	I also made it utilize pointers, by allocating memory for how large the array of floats would be and
	using a for loop to create all the values.
	
	**outputSound**
	I check if either the file or sound struct is null, if so I return a 1.
	I then check if the samples inside of the sound are null, indicating the memory wasnt allocated for it,
	if so I return a 1.
	Finally I iterate through all the samples in s and fprintf them to the file.
	
	


    