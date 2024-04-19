#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Trie structure
struct Trie
{	int occur;
    struct Trie* getWord[26];//remember that a trie is basically a fancy key array
    
};


// Initializes a trie structure
struct Trie *createTrie(){
    struct Trie* newTrie = (struct Trie*) malloc(sizeof(struct Trie));
    if(newTrie == NULL)
        return NULL;
    newTrie ->occur = 0;
    
    for(int i = 0; i < 26; i++)
        newTrie->getWord[i] = NULL;
    
    return newTrie;

}


// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word){    
    int length = strlen(word);
    struct Trie* curr = pTrie;
    for(int i = 0; i < length; i++){
        int letter = word[i] - 'a';
       
       if(curr ->getWord[letter] == NULL)
             curr ->getWord[letter]= createTrie();
       
       curr = curr -> getWord[letter];
    }

    
    curr -> occur ++;
    
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie* root = pTrie;
    int length =strlen(word);
    int letter;
    for(int i = 0; i < length; i++){
         letter = word[i] - 'a'; 
        if(root ->getWord[letter] == NULL)
            return 0;
        root = root ->getWord[letter];
    }

   
     return root ->occur;

}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie){
        for(int i = 0; i < 26; i++)
            deallocateTrie(pTrie ->getWord[i]);
        free(pTrie);
    } 
    return NULL;
}



// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
 
    FILE* file = fopen(filename, "r");
    

    if (file == NULL) {
        printf("Error opening the file.\n");
        return -1; 
    }

    int numWords;
    fscanf(file, "%d", &numWords);
   
    for (int i = 0; i < numWords; i++) {
         pInWords[i] = (char *)calloc(256, sizeof(char));
         fscanf(file, "%s", pInWords[i]);
        

    }

    fclose(file);

    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}