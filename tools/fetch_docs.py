#!/usr/bin/env python3
"""Fetch docs.slinky.gg module pages and extract settings (h2 + h3 children)."""
import json
import re
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OUT = ROOT / 'docs_modules_raw.json'
BASE = 'https://docs.slinky.gg'


def fetch(url):
    req = urllib.request.Request(url, headers={'User-Agent': 'Mozilla/5.0'})
    with urllib.request.urlopen(req, timeout=30) as r:
        return r.read().decode('utf-8', errors='ignore')


def extract_module_links(html):
    links = re.findall(r'href="(/modules/[^"]+)"', html)
    return sorted(set(l for l in links if l.count('/') >= 4 and not l.endswith('#_top')))


def extract_settings(page_html):
    body = re.sub(r'<script[^>]*>.*?</script>', '', page_html, flags=re.S)
    body = re.sub(r'<style[^>]*>.*?</style>', '', body, flags=re.S)
    body = re.sub(r'<a[^>]*class="[^"]*pagination[^"]*".*?</a>', '', body, flags=re.S)
    # Parse h2 sections; within each section, collect h3 headings
    sections = re.findall(
        r'<h2[^>]*>(.*?)</h2>\s*(.*?)(?=<h[12]|</main>|</article>|$)', body, re.S)
    settings = []
    for heading, sec_body in sections:
        htext = re.sub(r'<[^>]+>', '', heading).strip()
        if not htext or htext.lower() in ('overview', 'on this page'):
            continue
        # Find h3 children in this section
        h3s = re.findall(r'<h3[^>]*>(.*?)</h3>\s*(.*?)(?=<h[123]|</main>|</article>|$)', sec_body, re.S)
        if h3s:
            for h3_head, h3_body in h3s:
                h3text = re.sub(r'<[^>]+>', '', h3_head).strip()
                if not h3text:
                    continue
                desc = re.sub(r'<[^>]+>', ' ', h3_body)
                desc = re.sub(r'\s+', ' ', desc).strip()
                settings.append({'name': h3text, 'description': desc, 'section': htext})
        else:
            desc = re.sub(r'<[^>]+>', ' ', sec_body)
            desc = re.sub(r'\s+', ' ', desc).strip()
            settings.append({'name': htext, 'description': desc})
    return settings


def main():
    list_html = fetch(BASE + '/basics/get-started/')
    links = extract_module_links(list_html)
    modules = []
    for link in links:
        slug = link.rstrip('/').split('/')[-1]
        category = link.rstrip('/').split('/')[-2]
        name = slug.replace('-', ' ').title()
        try:
            page = fetch(BASE + link)
            settings = extract_settings(page)
        except Exception as e:
            settings = [{'name': 'FETCH_ERROR', 'description': str(e)}]
        modules.append({
            'module': name,
            'category': category.title(),
            'url': BASE + link,
            'settings': settings,
        })
        print(f"fetched {name}: {len(settings)} settings")
    OUT.write_text(json.dumps(modules, indent=2), encoding='utf-8')
    print(f"saved {OUT}")


if __name__ == '__main__':
    main()
