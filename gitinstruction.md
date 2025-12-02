
how to use the git. when in the folder you are working in, open a terminal your project folder since you already have the remote origin added you don't need to do anything other than this.

git pull

when finished working, make sure you do these terminal commands in order.

git add .
git commit -m "any message about the updates you made"
git push origin main

this will push the files you worked on into github so i can then pull your progress. 

if for some reason your remote origin becomes broken. open in terminal the folder that contains your project

git init
git add .
git commit -m "readding my remote origin"

git branch -M main
git remote add origin https://github.com/brandiballer/FinalProject-V2.git
git push -u origin main

then after everything is working again check with

git status

then you can do

git add .
git commit -m "your message"
git push