bin_PROGRAMS=game
game_SOURCES=game.c
pkgdata_DATA=ru/LC_MESSAGES/game.mo

messages.pot: game.pot game.c
	xgettext -k_ -c game.c -o messages.new.pot
	cp game.pot messages.pot
	msgmerge -U messages.pot messages.new.pot

ru.po: messages.pot
	msgmerge -U $@ $<

ru/LC_MESSAGES/game.mo: ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

run_en:
	./game

run_ru:
	LANGUAGE=ru_RU.UTF8 ./game

gitclean:
	git clean -xdf
