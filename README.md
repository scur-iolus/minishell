# minishell

## 📸 Quick preview

![minishell preview](https://i.ibb.co/F39dS7B/minishell.gif)

## 🎬 About this project

I've completed this project between October and December 2021 with a friend of mine. `minishell` is one of the mandatory projects that every 42 student has to complete as part of the core school curriculum. It had to be written in `C`. [42](https://42.fr/en/homepage/) is the first tuition-free computer training, open to all, regardless of diploma.

Here, our goal was to recreate a fairly basic shell based on the model of [bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell)), the most popular shell among Linux users and the default interactive shell on that operating system's various distributions. The project subject can be found [here](https://drive.google.com/file/d/13bsUBbHvaZZzdCMslFAoAXHPi0A6Z7HG/view?usp=sharing). In short, we had to implement several built-ins and to handle properly redirections, pipes, environment variables and some signals.

## 🐚 Great, but what is actually a shell?

Anything you can do with your mouse can be done through a shell with a keyboard.  When you open a terminal window and type commands, something has to take what you’ve typed, figure out what you intended, and run the tasks you asked for. The software that does this is the shell. A shell is a command interpreter, a convenient text interface to interact with your system. Before the appearance of more advanced graphic interfaces, it was the only possible interaction people had with their computer. Thus, it's a very critical piece of code. Let's give you a more concrete example: in a way, one could say that the [explosion of the rocket Ariane 5](https://en.wikipedia.org/wiki/Ariane_flight_V88) in 1996 is due to a badly designed shell.

## 🎯 Things I've learnt from this project

`minishell` was the first group project in my 42 cursus. Although I had already had opportunities to work on software development project as part of a team in the context of past internships, this project allowed me to question myself: how much was I familiar with [Git](https://en.wikipedia.org/wiki/Git)? Throughout this project, I was able to feel more conﬁdent about my skills in version control. Also, one of the issues we had to address was to distribute the workload in an equitable way.

Above all, `minishell` allowed me to understand more finely the inner workings of `bash`. The command-line interpreter is a central tool for every developer, nevertheless many non-experienced developers have only a superficial knowledge of it. Recoding from scratch such an essential programme is definitely the best way to master and to unlock the power of shell in many everyday situations. I've also learnt a lot about commands execution, system calls, file descriptors, memory leaks, forking processes, inter-process communication, signals management.

## 💡 Tips & useful resources

Here are some useful resources which could save time to future 42 school students:
- To get started, [this tutorial](https://brennan.io/2015/01/16/write-a-shell-in-c/) might help you,
- To get familiar with the concept of `pipe` and `fork`, [this series of videos](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY) is a must,
- Before starting to code, I recommend to get perfectly familiar with `bash`, to do as many tests as you can, in particular regarding the management of multiple layers of quotes: I wish I had read [this page](https://www.austintripp.ca/blog/2019/07/18/bash-quotes) or [this page](https://rg1-teaching.mpi-inf.mpg.de/unixffb-ss98/quoting-guide.html) earlier.
- When testing your programme and comparing it with `bash`, don't forget you can use broadcasting both [on iTerm](https://christopher.su/notes/mac/iterm-broadcast/) and [on Terminator](https://terminator-gtk2.readthedocs.io/en/latest/grouping.html#broadcasting-input-to-multiple-terminals).
