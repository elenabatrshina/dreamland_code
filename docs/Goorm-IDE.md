# Goorm Online IDE

**Содержание**
* [Cоздание новой учетной записи](#account)
* [Работа с проектом дримленд](#browse)
* [Сборка и запуск своего сервера](#build)
* [Совместная разработка](#collaboration)
* [Песочница](#sandbox)

Корейская компания Goorm бесплатно предоставляет онлайн-среду разработки в облаке и один контейнер для запуска своего кода, с доступом к нему как через браузер, так и по ssh. Помимо основного владельца, к одной и той же среде могут подключаться до 5 разработчиков одновременно, наблюдая за правками друг друга в реальном времени (shared cursor). Для проектов на С++ этой среде, конечно, далеко до полноценных IDE наподобие Visual Studio или Eclipse, но как минимум можно читать и править исходники с подсветкой синтаксиса, искать по всему проекту, быстро открывать нужные файлы, быстро перемещаться внутри файла и так далее. Есть поддержка работы с репозиторием, просмотр и сравнение разных версий, разрешения конфликтов.

Итак, если хочется поковыряться с исходниками и поэкспериментировать, но неохота для этого поднимать виртуальную машину или свой докер-контейнер, можно воспользоваться Goorm IDE. Создать свою учетную запись, скачать код дримленда, собрать его и запустить муд-сервер на стандартных портах 9000 и 9001. Эти же порты можно сделать доступными снаружи, и заходить в мир с помощью любого удобного клиента. 

Вот как выглядит запущенная среда в браузере и окно терминала поверх нее: 

![Goorm IDE with a terminal](https://dreamland.rocks/downloads/goorm01.png)

##  <a name="account">Cоздание новой учетной записи</a>

Вот какие шаги понадобятся для этого:

0. Убедиться, что у вас уже есть учетная запись на гитхабе и создан форк репозитория [dreamland_code](https://github.com/dreamland-mud/dreamland_code) как описано в [инструкции](https://github.com/dreamland-mud/dreamland_code/#git).
1. Создать новый аккаунт на https://goorm.io, перейти на https://ide.goorm.io, кликнуть на Dashboard
2. Там вы увидите сводную инфу по бесплатному аккаунту и кнопку Create a New Container, нажмите на нее.
3. В появившейся форме введите свой логин/пароль на Github, выберите нужный репозиторий из списка, тип контейнера - C/C++, template - C/C++ Console Project:

![Create new container](https://dreamland.rocks/downloads/goorm05.png)

## <a name="browse">Работа с проектом дримленд</a>

С этого момента можно начинать бродить по исходникам. Полезные сочетания горячих клавиш
(их всех можно переопределить по нажатию на меню Goorm IDE -> Properties или Alt+P)

* Иконка Find: поиск внутри файла

![Icons](https://dreamland.rocks/downloads/goorm15.png)

* Иконка Search: поиск по всему проекту с подсветкой результатов и быстрому переходу по клику на результат

![Search query](https://dreamland.rocks/downloads/goorm12.png)
![Search result](https://dreamland.rocks/downloads/goorm11.png)

* Быстрый переход к нужному файлу по имени: Alt+Shift+F

![Navigation](https://dreamland.rocks/downloads/goorm14.png)

## <a name="build">Сборка и запуск своего сервера</a>

По сути необходимо проделать те же шаги, что и на любом другом окружении c операционной системой Ubuntu, как описано в [инструкции](https://github.com/dreamland-mud/dreamland_code/#env): cкачать нужные пакеты, сконфигурировать исходники и скомпилировать их. Для удобства в каталоге admin/goorm лежат несколько скриптов, которые выполнят все эти действия. 

* Кликните на окно терминала и запустите сперва скрипт **init.sh**. Он скачает и установит все необходимые пакеты:

![init.sh](https://dreamland.rocks/downloads/goorm06.png)

* Затем запустите подряд **config.sh** и **build.sh**. И отправляйтесь пить чай на час. Именно столько занимает сборка всех исходников на довольно маломощном контейнере, который Goorm предоставляет для бесплатных учетных записей.
С другой стороны, даже если потом менять исходники, пересобирать придется только один-два измененных плагина, а это довольно быстро.

* Для краткости можно запустить все три разом, например:
```bash
cd admin/goorm
./init.sh && ./config.sh && ./build.sh
```
* Запустить сервер дримленд можно с помощью скрипта **run.sh**:

![run.sh](https://dreamland.rocks/downloads/goorm16.png)

* Зайти в мир можно, запустив еще один терминал (меню Window -> New Terminal Window или Alt+Shift+T) и набрав там 
```bash
telnet localhost 9000
```
Кодировка UTF-8, имя персонажа Kadm, пароль KadmKadm.

* Для более удобной работы можно использовать обычный муд-клиент. Нажмите на кнопку Port Forwarding и задайте forwarding для портов 9000 и/или 9001:

![Port Forwarding](https://dreamland.rocks/downloads/goorm13.png)

Теперь можно соединяться с муд-сервером по адресу ```52.78.43.69 53802```.

## <a name="collaboration">Совместная разработка</a>

Можно пригласить других разработчиков в вашу среду, сообщив им краткий URL рядом с кнокой Share:

![Share](https://dreamland.rocks/downloads/goorm17.png)

В правой панели на вкладке Collaboration будет видно всех, кто присоединился, и появится чат:

![Collaboration](https://dreamland.rocks/downloads/goorm18.png)

Также можно приглашать коллег, нажав на вкладку Friends и отправив им приглашение по почте.

## <a name="sandbox">Песочница</a>

Можно поиграться с уже существующим окружением, запущенным из-под тестового аккаунта dreamlandtest. 
Ссылка: https://goor.me/KNxn

Окружение будет доступно не всегда, а только если его владелец работал с ним в течение прошедших 2х часов.
По прошествии 2х часов неактивные контейнеры ставятся на паузу.



