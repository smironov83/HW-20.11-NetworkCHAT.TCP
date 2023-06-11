#HW-20.11-NetworkCHAT.TCP
NetworkCHAT.TCP - Это итоговое задание по третьему модулю курса «Разработчик на C++» от oнлайн-школы 
SkillFactory, "Основы Linux и программирование в Linux на C/С++".


#  Список команды:
|  Логин        |  Фамилия Имя 
| ------        | ------                                                   
| smironov83    | Миронов Сергей        

`smironov83` - all-in-one

В NetworkCHAT.TCP реализовано:
- Сетевой двух-пользовательский чат на базе сокетов.
- Архитектура клиент-сервер.
- Кроссплатформенность. Приложение полноценно работает с Linux и Windows в исходном виде.
- Поддержка символов кириллицы при работе клиента и сервера на разных платформах.
- Собственное решение перекодирования 16-битной UTF-8 кодировки в однобайтовую Windows-1251 и обратно.
- Работа с системным временем на платформе Linux и Windows.
- Индивидуальный Nickname без ограничений по вводу.
- Отображение Nickname и даты/времени отправки в каждом сообщении.
- Отправка/прием сообщений поочередное.

Особенности реализации:
- Использован протокол TCP.
- Код максимально универсален (Linux/Windows) и един для обоих платформ.
- Для поддержки символов кириллицы используется передача сообщений исключительно в кодировке UTF-8.
- На платформе Linux сообщения принимаются и отправляются в текущей кодировке ОС UTF-8.
- На платформе Windows все сообщения при отправке и приемке перекодируются в UTF-8 и обратно.
- Для корректной работы необходимо сначала авторизоваться на серверной части приложения, иначе клиентское завершится с ошибкой подключения.
- В зависимости от особенностей архитектуры сети может потребоваться изменение IP адреса сервера в клиентском части, по умолчанию используется 127.0.0.1.
- Отправка сообщений начинается с клиентской части. Сервер при запуске встает на прием.
- Ввод команды exit на одном из устройств инициирует закрытие сокетов и завершение работы приложения на обоих устройствах.

#  Тестирование:
|  Логин        |  Фамилия Имя 
| ------        | ------                                                   
| smironov83    | Миронов Сергей        



> Чтобы пользователь не заскучал, пока его друзья оффлайн, реализован пользователь чат-бот. 
> Его ответы попадают всегда в точку. 
> Он лучше всяких исскуственных интелектов ChatGPT

#  Классы, реализованные в UnworkableChat

| Наименование класса	  | Содержание класса																																								|
| ------				  | ------																																											|
| user					  | `Шаблонный класс user`. `Реализация в заголовочном файле`. `Хранит значения пользователей: логин, пароль, имя, статус нахождения в сети, история переписки`. `Хеширует пароли`. |
| message				  | `Класс message`. `Конструирует сообщение в чате по шаблону, использует введенный текст, системные дату и время`.																|
| command_module		  | `Класс command_module`.`Описаны массивы значений класса user и словарь автодополнения`.	`Реализует все пользовательские функции и команды, предусмотренные программой.`			|
| autocomplete_dictionary | `Класс autocomplete_dictionary`. `Реализует функции автодополнения`. `Хранение и поиск слов в префиксном дереве`.																|

#  Не одно отправленное сообщение не потеряется!
