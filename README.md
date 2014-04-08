EDA031-Project
==============

Hemliga kommandon:

g++ -o news_server_swag_edition src/server/server_main_swag_edition.cc src/server/server_command_handler.cc src/server/main_database.cc src/common/server.cc src/common/message_handler.cc src/common/connection.cc -std=c++11

g++ -o news_server src/server/server_main.cc src/server/server_command_handler.cc src/server/cache_database.cc src/common/server.cc src/common/message_handler.cc src/common/connection.cc -std=c++11



Syntaxen för användarkommandon är just nu:

	list -> listar alla grupper

	list # -> listar alla artiklar i gruppen med ID #

	read # -> läser artikel # i gruppen som man listade i förra kommandot. 
	Kommandot antar alltså att användaren skrivit list #

	create group [group name] -> skapar en grupp med namnet [group name]

	create article -> skapar en ny artikel. 
	Användaren får sen mata in gruppID, titel, författare och brödtext.

	delete group # -> tar bort gruppen med ID #.

	delete article # -> tar bort artikel nr # från den grupp man listat i föregående kommando. 
	Kommandot antar alltså att man listat en grupp med list #.



A fabulous project with lots of things, gismos, objects, and stuff.

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
