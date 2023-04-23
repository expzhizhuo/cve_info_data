# Fast-GitHub

![Chrome Web Store](https://img.shields.io/chrome-web-store/v/mfnkflidjnladnkldfonnaicljppahpg?style=for-the-badge)
![Chrome Web Store](https://img.shields.io/chrome-web-store/users/mfnkflidjnladnkldfonnaicljppahpg?style=for-the-badge)



# INTRODUCTION

Github download speeds are generally slow in Asia, and with this plugin the download speeds will be insane!

[![Page Views Count](https://badges.toozhao.com/badges/01EH1R0YMQANV1ACQXTEBK7JCN/green.svg)](https://badges.toozhao.com/badges/01EH1R0YMQANV1ACQXTEBK7JCN/green.svg "Get your own page views count badge on badges.toozhao.com")



# Download

<table>
<tbody>
<tr>
<td>
<a href="https://chrome.google.com/webstore/detail/github%E5%8A%A0%E9%80%9F/mfnkflidjnladnkldfonnaicljppahpg" target="_blank">
        <img src="https://i.loli.net/2021/04/23/IqpU7COKQvzrcyG.png" />
      </a>
</td>
<td><a href="https://apps.apple.com/cn/app/fastgithub/id1564025982?mt=12" target="_blank">
        <img src="https://i.loli.net/2021/04/23/SKsywoGWg1HvEja.png" />
      </a></td>
<td>
<a href="https://microsoftedge.microsoft.com/addons/detail/github%E5%8A%A0%E9%80%9F/alhnbdjjbokpmilgemopoomnldpejihb" target="_blank">
        <img src="https://i.loli.net/2021/04/23/EnS3eDi4I86Yv2N.png" />
      </a>
</td>
<td><a href="https://addons.mozilla.org/en-US/firefox/addon/fastgithub/" target="_blank">
        <img src="https://i.loli.net/2021/04/23/4wGaRTisEdcBnIt.png" />
      </a></td>
</tr>
</tbody>
</table>

# Preview

![MNOt8347RDGmnjo](https://i.loli.net/2021/04/23/MNOt8347RDGmnjo.png)

![9UPXkGsHzw5hiru](https://i.loli.net/2021/04/23/9UPXkGsHzw5hiru.png)


# How to use SSH channels

Configuring user profiles (`~/.ssh/config`)

```bash
Host github.com
        HostName github.com
        User git
        IdentityFile Specify the path to the private key file used for key authentication
# Add the following
Host git.zhlh6.cn
        HostName git.zhlh6.cn
        User git
        IdentityFile Using the secret key of github.com
```

Testing SSH Connections

```bash
ssh -T git@git.zhlh6.cn

# successful
You've successfully authenticated, but GitHub does not provide shell access
```

---
