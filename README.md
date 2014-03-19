EDA031-Project
==============

A fabolous project with lots of things, gismos, objects, and stuff.

	Johans informativa git-skola! (Godkänd av Beatrice Ask)
	
	öppna terminalen!
	navigera till mappen du vill jobba i! Skriv sen:

	> git init

	// sätter origin som alias för länken till repot
	> git remote add origin https://github.com/johan1a/EDA031-Project 

	// drar ner allt från master-branchen hos origin, just nu bara en readme-fil
	> git pull origin master

	// för att lägga till saker för commit:
	> git add * // lägger till allt
	> git add src/schysstklass.cc // lägger bara till src/schystklass.cc

	// för att visa vad du lagt till i din kommande commit:
	>git status 

	// commitar men pushar inte till repot
	>git commit -m "informativt meddelande" 

	// pushar upp allt i din commit till repot, lösenord osv behövs
	>git push origin master
