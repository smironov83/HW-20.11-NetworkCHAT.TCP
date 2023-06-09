#HW-20.11-NetworkCHAT.TCP
NetworkCHAT.TCP - Это итоговое задание по третьему модулю курса «Разработчик на C++» от oнлайн-школы 
SkillFactory, "Основы Linux и программирование в Linux на C/С++".

#  Состав решения:
- HW-20.11-Server
- HW-20.11-Client

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
|   OS Server   |   OS Client   | Итоги тестирования |   Примечания   |
| ------        | ------        | ------             | ------         |
| Windows 11 v.22H2 (лок.маш. MSI Modern 14 C12M) | Windows 11 v.22H2 (лок.маш. MSI Modern 14 C12M) | Все заявленные функции успешно работают | Запуск на одной платформе |
| Windows 11 v.22H2 (лок.маш. MSI Modern 14 C12M) | Ubuntu 22.04.2 LTS (вирт.маш.Oracle VM VirtualBox) | Все заявленные функции успешно работают | Тип подключения - сетевой мост, использование IP адреса лок.машины |
| Ubuntu 22.04.2 LTS (вирт.маш.Oracle VM VirtualBox) | Windows 11 v.22H2 (лок.маш. MSI Modern 14 C12M) | Все заявленные функции успешно работают | Тип подключения - NAT, проброс портов на IP адрес по умолчанию |
| Ubuntu 22.04.2 LTS (вирт.маш.Oracle VM VirtualBox) | Ubuntu 22.04.2 LTS (вирт.маш.Oracle VM VirtualBox) | Все заявленные функции успешно работают | Запуск на одной платформе |

#  Комментарий разработчика:
> Принято решение создать отдельное приложение сетевого чата для закрепления полученных знаний.
> Основной проект чата планируется доработать до сетевой версии после изучения многопоточного программирования, т.к. не вижу свой текущий проект в режиме "рации" в толпе клиентских сокетов, ждущих своей очереди на сервере.
> Кроме того планирую в сетевой версии существенно изменить структуру приложения. Что также предполагается сделать с учетом многопоточности.

#  Классы, реализованные в HW-20.11-Client:

| Наименование класса	| Содержание класса	|
| ------ | ------	|
| user | `Реализация в заголовочном файле`. `Хранит имя пользователя и историю переписки`. `Хеширует пароли`. `Конструирует сообщение в чате по шаблону, используя введенный текст, системные дату и время`. `Переводит сообщения из кодировки UTF-8 в Windows-1251 при приеме в среде Windows`. `Переводит сообщения из кодировки Windows-1251 в UTF-8 при отправке`. |
| network_client | `Реализация в .h и .cpp файлах`. `Создает клиентский сокет`. `Подключается к серверу`.	`Отправляет сообщения`.	`Принимает сообщения`. `Закрывает соединение`. `Уведомляет об ошибках на всех этапах взаимодействия с сетью и завершает работу программы`.|

#  Классы, реализованные в HW-20.11-Server:

| Наименование класса	| Содержание класса	|
| ------ | ------	|
| user | `Реализация в заголовочном файле`. `Хранит имя пользователя и историю переписки`. `Хеширует пароли`. `Конструирует сообщение в чате по шаблону, используя введенный текст, системные дату и время`. `Переводит сообщения из кодировки UTF-8 в Windows-1251 при приеме в среде Windows`. `Переводит сообщения из кодировки Windows-1251 в UTF-8 при отправке`. |
| network_server | `Реализация в .h и .cpp файлах`. `Cоздает сокет для подключения клиента`. `При подключении клиента создает клиентский сокет`.	`Отправляет сообщения`.	`Принимает сообщения`. `Закрывает соединение`. `Уведомляет об ошибках на всех этапах взаимодействия с сетью и завершает работу программы`.|

#  Ни одно отправленное сообщение не потеряется!
