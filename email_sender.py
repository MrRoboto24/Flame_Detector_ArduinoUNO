import smtplib

my_email = "xxxxxxxxx@gmail.com"
password = "xxxxxxxxxxxxxxxx"

with open("fire_alarm.txt","r") as file:
    message = file.read()

with smtplib.SMTP("smtp.gmail.com") as connection:
        connection.starttls()
        connection.login(user=my_email, password=password)
        connection.sendmail(from_addr=my_email,
                            to_addrs="emailaddress",
                            msg=f"Subject:Fire Alarm Activation - Please Evacuate Immediately\n\n{message}")
