# Markov Chain

A markov chain is a method of predicting a future occurence of a state by taking into account the previous states that occurred before the current state.

The way this project works is by taking an input file with a corpus of text and generating the next word with the highest probability from the corpus of text.

# Use case

User will be able to upload a corpus of text and randomly generate a sequence of tokens starting from a random start point that have the highest probability of following the start state. This is simply a prototype for more complex natural language processing tasks since a markov chain is memoryless.

# To run locally:

1. npm i in front end, then npm start.
2. npm i in back end, then node server.js
3. go to localhost:8080 and upload a file, see the markov chain try to predict the next sequence of words.