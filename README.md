#create a new repository
echo "# bic1project" >> README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin https://github.com/safullah/bic1project.git
git push -u origin master

#already existing git repository
git remote add origin https://github.com/safullah/bic1project.git
git push -u origin master

