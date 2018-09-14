package main

import (
	"fmt"
	"strconv"
)

type UrlGenerator interface {
	idToShortUrl(uint64) (string)
	shortUrlToId(string) (uint64)
}

type UrlGeneratorImpl struct {
}

func reverse(s string) string {
	runes := []byte(s)

	return string(runes)
}

func (ug *UrlGeneratorImpl) idToShortUrl(id uint64) (string){
	basechar := []byte("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")

	shortUrl := make([]byte, 6)
	index := 0
	for id!=0 {
		shortUrl[index] = basechar[id%62]
		id = id/62
		index ++
	}
	fmt.Println(string(shortUrl))
	for i,j:=0, len(shortUrl)-1; i<j; i,j = i+1,j-1 {
		shortUrl[i], shortUrl[j] = shortUrl[j], shortUrl[i]
	}
	return string(shortUrl)
}

func (ug *UrlGeneratorImpl) shortUrlToId(shorturl string) (uint64){
	var id int

	url := []byte(shorturl)
	for i:=0; i<len(url);i++ {
		switch {
		case url[i]>='a' && url[i]<='z':
			id = id*62 + int(url[i])-'a'
		case url[i]>='A' && url[i]<='Z':
			id = id*62 + int(url[i])-'A'+26
		case url[i]>='0' && url[i]<='9':
			id = id*62 + int(url[i])-'0'+52
		}
	}
	return uint64(id)
}

func main() {
	ug  := UrlGeneratorImpl{}

	var cmd string
	for {
		fmt.Scanln(&cmd)
		if val,err := strconv.Atoi(cmd); err==nil {
			// isdigit
			ret := ug.idToShortUrl(uint64(val))
			fmt.Println("%s %s %s", cmd, val ,ret)
		} else {
			fmt.Println(cmd)
			ret := ug.shortUrlToId(cmd)
			fmt.Println("tur: ", ret)
		}
	}
}
