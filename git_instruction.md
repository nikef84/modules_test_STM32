# Минимальный набор комманд для гита

## Клонирование репозитория

Чтобы клонировать репозиторий нужно в гите перейти в папку, где планируется хранить репозиторий. Либо с помощью `cd`:

```cd d:/chibistudio20v0/workspace```

Либо в проводнике правой кнопкой мышкой в желаемой папке `Git Bash Here`.

После этого вызываем функцию `git clone` и указываем адрес репозитория:

``` git clone https://github.com/lsd-maddrive/Awesome_TAU_Stand.git```

## Как сделать коммит

Любые локальные изменения в репозитории должны фиксироваться с помощью коммитов. Для этого нужно сначала добавить изменеия к будщему коммиту с помощью `git add`. Аргументом являются файлы изменения в которых нужно зафиксировать. Можно писать `-A`, чтобы подгрузить сразу все.

``` git add -A```

После это нужно собственно сделать коммит с помощью `git commit` Обязательным аргументом надо дать комментарий к коммиту.

``` git commit -m 'some text' ```

Перед коммитом имеет смысл проверить состояние репозитория с помощью `git status`.

## Работа с удаленным репозиторием

Для того чтобы стянуть себе актуальную версию репозитория нужно выполнить `git pull`. Чтобы залить свои изменения на удаленный репозиторий - `git push`.

*ВАЖНО!* Запушить изменения можно только в том случае, если локальный репозиторий не отстает от удаленного. То есть локально должна быть актуальная версия репозитория + некоторые изменения.

Могут возникнуть конфликты. Если локальная версия отстает от удаленного репозитория и локальные изменения затрагивают уже существующие различия, система не поймет какой из вариантов правильный. В этом случае надо будет решать конфликты руками.

## Работа с ветками

Ветку можно создать в удаленном репозитории с помощью выпадающего меню слева от названия репозитория (над этим блоком текста). По ссылке `View all branches` будет страница управления всеми ветками где можно создать новую.

Создав новую ветку надо рассказать о ней локальному репозиторию с помощью `git fetch`. После этого на нее можно переключится чтобы создать локальную версию с помощью `git checkout`:

``` git fetch
git checkout branch_name
```

Либо можно сначала создать локальную ветку с помощью того же `git checkout` с аргументом `-b`, который создаст новую ветку. После этого ее надо будет запушить в удаленный репозиторий сообщив что это новая ветка:

``` git checkout -b branch-name
делаем в ветке важные дела
git add -A
git commit -m 'comment'
git push --set-upstream origin branch-name
```

После этого между ветками можно в любой момент переключаться с помощью `git checkout`.

## Прокси

В ЛЭТИ используется прокси сервер о котором отдельно надо сообщить гиту:

``` git config --global http.proxy http://10.128.0.90:8080 ```

Чтобы прекратить использование прокси:

``` git config --global --unset http.proxy ```

## Сохранение персональных данных

Имя пользователя:

``` git config --global user.name "GeeksforGeeks" ```

Почта:

``` git config --global user.email "GFGexample@gmail.orgg" ```

Пароль:

``` git config --global user.password "1234321" ```

Сохранить данные навсегда:

``` git config --global credential.helper store ```

Проверить сохранёные данные:

``` git config --list --show-origin ```

# Заключение

Здесь описан самый минимум комманд для работы с гитом. Если хотите научится большему - в сети можно найти бесконечное количество различной информации в том числе на русском языке.